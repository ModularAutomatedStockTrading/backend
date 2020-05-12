//const NNengine = require('build/Release/NN_engine.node');

/*const evolutionaryTrainer = new NNtrainer.EvolutionaryTrainer(
    layercount : int,
    model_array : int[], // model_array[i] = amount of nodes in i'th layer
    amount_of_datapoint : int,
    input_size : int,
    data_points_input : [[int]],
    output_size : int,
    data_points_output : [[int]],
);

evolutionaryTrainer.train(
    lower_stuff : int,
    upper_stuff : int,
    amount_of_generations : int,
    instances_per_generation : int
) --> [
    [
        [int]
    ],
    [
        [int]
    ],
    [
        [int]
    ],
    [
        [int]
    ],
]*/

const NNengine = require('build/Release/NN_engine.node');

const {getInputData, getAPIurlInput} = require("src/server/services/inputs")
const {getOutputData, getAPIurlOutput} = require("src/server/services/outputs")
const {fetchFromAPI} = require("src/server/utility/alphavantageAPI")
const minMaxNormalize = require("src/server/utility/normalization").minMax;

module.exports = class ModelService{
    constructor(model){
        console.start("MODEL SERVICE")
        console.log("initializing model service...")
        this.model = model;
        this.inputs = []
        this.outputs = []
        this.weights = []
        this.trainingInputs = []
        this.trainingOutputs = []
        this.testInputs = []
        this.testOutputs = []
        this.statistics = {}
    }

    fetchTrainingData(){
        console.log("fetching data...")
        return new Promise((resolve, reject) => {
            const fetchingPromises = []
            const dataPromises = []
            const urls = {};
            for(const input of this.model.inputs){
                const url = getAPIurlInput(input);
                if(urls[url]){
                    urls[url].push({
                        type : "input",
                        input
                    });
                }else{
                    urls[url] = [{
                        type : "input",
                        input
                    }];
                }
            }
            for(const output of this.model.outputs){
                const url = getAPIurlOutput(output);
                if(urls[url]){
                    urls[url].push({
                        type : "output",
                        output
                    });
                }else{
                    urls[url] = [{
                        type : "output",
                        output
                    }];
                }
            }
            for(const url in urls){
                fetchingPromises.push(new Promise((resolveRequest, rejectRequest) => {
                    fetchFromAPI(url).then(() => {
                        for(const query of urls[url]){
                            if(query.type == "input"){
                                dataPromises.push(getInputData(query.input));
                            }else{
                                dataPromises.push(getOutputData(query.output));
                            }
                        }
                        resolveRequest();
                    })
                }))
            }
            Promise.all(fetchingPromises).then(() => {
                Promise.all(dataPromises).then(results => {
                    for(const time in results[0].datapoints){
                        let b = true;
                        for(let i = 0; i < results.length; i++){
                            if(results[i].datapoints[time] == undefined){
                                b = false;
                                break;
                            }
                        }
                        if(b){
                            const inputVector = []
                            const outputVector = []
                            for(let i = 0; i < results.length; i++){
                                if(results[i].type == 'input'){
                                    inputVector.push(results[i].datapoints[time])
                                }else{
                                    outputVector.push(results[i].datapoints[time])
                                }
                            }
                            this.inputs.push(inputVector)
                            this.outputs.push(outputVector)
                        }
                    }
                    resolve()
                })
            })
        })
    }

    test(){
        console.log("testing neural network...")
        if(this.testInputs.length == 0) return;
        const neuralNetwork = new NNengine.NNExecutor(
            this.weights.length,
            this.weights,
            true
        );
        const differences = [];
        const corrects = [];
        const truePositives = [];
        const trueNegatives = [];
        const falsePositives = [];
        const falseNegatives = [];
        for(const i in this.testOutputs[0]){
            differences.push(0);
            corrects.push(0);
            truePositives.push(0);
            trueNegatives.push(0);
            falseNegatives.push(0);
            falsePositives.push(0);
        }
        for(const i in this.testInputs){
            const outputVector = neuralNetwork.predict(
                this.testInputs[i].length,
                this.testOutputs[i].length,
                this.testInputs[i]
            );
            for(const j in outputVector){
                differences[j] += Math.abs(outputVector[j] - this.testOutputs[i][j])
                const isCorrect = (outputVector[j] > 0.5 == this.testOutputs[i][j]);
                corrects[j] += isCorrect;
                truePositives[j] += outputVector[j] > 0.5 && isCorrect;
                trueNegatives[j] += outputVector[j] <= 0.5 && isCorrect;
                falsePositives[j] += outputVector[j] > 0.5 && !isCorrect;
                falseNegatives[j] += outputVector[j] <= 0.5 && !isCorrect;
            }
        }
        this.statistics = {
            differences : differences.map(difference => {
                return difference / this.testOutputs.length
            }),
            corrects : corrects.map(correct => {
                return correct / this.testOutputs.length
            }),
            F1scores : (() => {
                const res = [];
                for(let i = 0; i < this.testOutputs[0].length; i++){
                    const precision = truePositives[i] / (truePositives[i] + trueNegatives[i]);
                    const recall = truePositives[i] / (falseNegatives[i] + truePositives[i]);
                    res.push(precision * recall / (precision + recall) * 2); // https://en.wikipedia.org/wiki/F1_score
                }
                return res;
            })()
        }
    }

    train(){
        
        const inputs = minMaxNormalize(this.inputs);

        this.trainingInputs = getSubarrayOfData(inputs, 0.8, true);
        this.trainingOutputs = getSubarrayOfData(this.outputs, 0.8, true);
        this.testInputs = getSubarrayOfData(inputs, 0.8, false);
        this.testOutputs = getSubarrayOfData(this.outputs, 0.8, false);

        console.log(this.trainingInputs);
        console.log(this.trainingOutputs);
        console.log(this.testInputs);
        console.log(this.testOutputs);

        return new Promise((resolve, reject) => {
            if(this.inputs.length < 10) resolve(null);
            console.log("training")
            console.log("Amount of datapoints:", inputs.length)
            const modelArray = 
                [this.model.amountOfInputNodes + 1]
                .concat(this.model.amountOfHiddenLayerNodes.map(el => el + 1))
                .concat([this.model.amountOfOutputNodes])
            ;
            this.evolutionaryTrainer = new NNengine.EvolutionaryModelTrainer(
                this.model.amountOfHiddenLayers + 2,
                modelArray,
                this.trainingInputs.length,
                this.trainingInputs[0].length,
                this.trainingInputs,
                this.trainingOutputs[0].length,
                this.trainingOutputs,
                true
            );
            this.weights = this.evolutionaryTrainer.train(0.5, 10, 10);
            this.test();
            resolve({
                weights : this.weights,
                statistics : this.statistics
            });
            console.stop()
        })
    }
}

const getSubarrayOfData = (data, amount, isFromStart) => {
    const length = Math.round(data.length * amount);
    if(isFromStart){
        return data.slice(0, length)
    }else{
        return data.slice(length, data.length);
    }
}
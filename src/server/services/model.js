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
        this.model = model;
        this.inputs = []
        this.outputs = []
        console.log("created model service")
    }

    fetchTrainingData(){
        console.log("fetching data")
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

    train(){
        const inputs = minMaxNormalize(this.inputs);
        //console.log(inputs);
        //console.log(this.outputs);
        return new Promise((resolve, reject) => {
            if(this.inputs.length < 10) resolve(null);
            console.log("training")
            console.log("   Amount of datapoints:", inputs.length)
            const modelArray = 
                [this.model.amountOfInputNodes + 1]
                .concat(this.model.amountOfHiddenLayerNodes.map(el => el + 1))
                .concat([this.model.amountOfOutputNodes])
            ;
            this.evolutionaryTrainer = new NNengine.EvolutionaryModelTrainer(
                this.model.amountOfHiddenLayers + 2,
                modelArray,
                inputs.length,
                inputs[0].length,
                inputs,
                this.outputs[0].length,
                this.outputs,
                true
            );
            const result = this.evolutionaryTrainer.train(0.5, 10, 10)
            resolve(result);
        })
    }
}
//const NNengine = require('build/Release/NN-engine');

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

const {getInputData} = require("src/server/services/inputs")
const {getOutputData} = require("src/server/services/outputs")

module.exports = class ModelService{
    constructor(model){
        this.model = model;
        this.inputs = []
        this.outputs = []
        console.log(model)
    }

    fetchTrainingData(){
        return new Promise((resolve, reject) => {
            const promises = []
            for(const input of this.model.inputs){
                promises.push(getInputData(input));
            }
            for(const output of this.model.outputs){
                promises.push(getOutputData(output));
            }
            Promise.all(promises).then(results => {
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
    }

    train(){
        console.log(this.inputs)
        console.log(this.outputs)
        return new Promise((resolve, reject) => {
            if(this.inputs.length < 10) resolve(null);
            const modelArray = 
                [this.model.amountOfInputsNodes]
                .concat(this.model.amountOfHiddenLayerNodes)
                .concat([this.model.amountOfOutputNodes])
            ;
            /*
            this.evolutionaryTrainer = new NNengine.EvolutionaryTrainer(
                this.model.amountOfHiddenLayers + 2,
                modelArray,
                this.inputs.length,
                this.inputs[0].length,
                this.inputs,
                this.outputs[0].length,
                this.outputs
            );
            const result = this.evolutionaryTrainer.train(0.95, 1.05, 100, 100)
            resolve(result)
            */
        })
    }
}
//const NNtrainer = require('build/Release/test');

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

module.exports = class Model{
    constructor(model){
        console.log(model)
    }

    train(){
        return new Promise((resolve, reject) => {
            resolve("result")
        })
    }
}
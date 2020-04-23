const testAddon = require('./build/Release/NN_engine.node');
const test = new testAddon.EvolutionaryModelTrainer(2, [1,1], 2, 3, [[1,1,1],[1,1,1]], 1, [[1], [1]]);

/*module.exports = class Model{
    constructor(model){
        console.log(model)
    }
}*/
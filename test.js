const testAddon = require('./build/Release/testaddon.node');
const prevInstance = new testAddon.EvolutionaryModelTrainer(2, [1,1], 2, 3, [[1,1,1],[1,1,1]], 1, [[1], [1]]);
console.log(prevInstance.getInputSize());
/*module.exports = class Model{
    constructor(model){
        console.log(model)
    }
}*/
const NNEngine = require('./build/Release/NN_engine.node');
try{
    const Trainer = new NNEngine.EvolutionaryModelTrainer(3, [1,3,3,3,1], 2, 1, [[0],[1]], 1, [[1], [0]]);
    console.log(Trainer.Train(0.1, 100, 100));
    // -0.1 --- 0.1
}catch(e){
    console.log(e)
}

/*module.exports = class Model{
    constructor(model){
        console.log(model)
    }
}*/
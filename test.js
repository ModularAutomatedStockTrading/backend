const NNEngine = require('./build/Release/NN_engine.node');
try{
    const Trainer = new NNEngine.EvolutionaryModelTrainer(2, [1,1], 2, 3, [[1],[1]], 1, [[1], [1]]);
    console.log(Trainer.Train(0.3, 2, 10));
}catch(e){
    console.log(e)
}

/*module.exports = class Model{
    constructor(model){
        console.log(model)
    }
}*/
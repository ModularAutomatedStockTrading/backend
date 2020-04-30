const NNEngine = require('./build/Release/NN_engine.node');
//TRAINING
/*try{
    const Trainer = new NNEngine.EvolutionaryModelTrainer(
        2, [2,1], 2, 1, [[0],[1]], 1, [[1], [0]], true
    );
    console.log(Trainer.train(0.1, 1000, 100));
    // -0.1 --- 0.1
}catch(e){
    console.log(e)
}*/


//EXECUTER
const executer = new NNEngine.NNExecutor(
    2,1,1,
    [[[1]],[[0]]],
    true
)

console.log(executer.predict(1,1,[1]))

/*module.exports = class Model{
    constructor(model){
        console.log(model)
    }
}*/
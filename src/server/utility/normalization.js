
const minMax = inputs => {
    const dimensions = inputs.length == 0 ? - 1 : inputs[0].length;
    if(dimensions == -1) return [];
    const res = []
    for(let i = 0; i < inputs.length; i++){
        res.push((() => {
            const temp = []
            for(let j = 0; j < dimensions; j++){
                temp.push(-1);
            }
            return temp;
        })())
    }
    for(let i = 0; i < dimensions; i++){
        let mi = Number.POSITIVE_INFINITY;
        let ma = Number.NEGATIVE_INFINITY;
        for(let j = 0; j < inputs.length; j++){
            mi = Math.min(inputs[j][i], mi);
            ma = Math.max(inputs[j][i], ma);
        }
        for(let j = 0; j < inputs.length; j++){
            res[j][i] = (inputs[j][i] - mi)/(ma - mi);
        }
    }
    return res;
}

module.exports = {
    minMax
}

/*console.log(minMax([
    [1,4,-1],
    [3,3,-2],
    [100,4,-10],
    [50,-4,-5]]
))*/
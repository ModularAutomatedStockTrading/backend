const {fetchFromAPI, getURL} = require("src/server/utility/alphavantageAPI")

const companies = ["MSFT", "SNE", "XIACF", "IBM"]
const companyStockIndicators = ["open", "high", "low", "close", "volume"]
const indicatorActions = ["UP", "DOWN"];
const amounts = [0,1,2,3,4,5,10,15,20,30,50,100,250,500,1000];

module.exports.getAPIurlOutput = output => {
    const type = output.type.split("/")
    const value = output.value.split("/")
    if(value[0] == 'stock'){
        const company = value[1];
        return getURL({
            function : "TIME_SERIES_INTRADAY",
            symbol : company,
            interval : "1min",
            outputsize : "full"
        })
    }
    return "";   
}

module.exports.getOutputs = () => {
    const res = []
    for(const company of companies){
        const companyOptions = []
        for(const indicator of companyStockIndicators){
            const indicatorOptions = []
            for(const action of indicatorActions){
                for(const amount of amounts){
                    companyOptions.push({
                        type : `stock/${indicator}/${action}/${amount}`,
                        label : `${company} stock ${indicator} ${action}-${amount}`,
                        value : `stock/${company}/${indicator}/${action}/${amount}`
                    })
                }
            }
        }
        res.push({
            label : company,
            options : companyOptions
        })
    }
    return res;
}

module.exports.getOutputData = output => new Promise((resolve, reject) => {
    const type = output.type.split("/")
    const value = output.value.split("/")
    if(value[0] == 'stock'){
        const company = value[1];
        const indicator = value[2];
        const action = value[3];
        const amount = value[4];
        //console.log(output, company, indicator, action, amount)
        setTimeout(() => fetchFromAPI({
            function : "TIME_SERIES_INTRADAY",
            symbol : company,
            interval : "1min",
            outputsize : "full"
        }).then(response => {
            //console.log(response)
            const res = {}
            const indicatorKey = `${companyStockIndicators.indexOf(indicator)+1}. ${indicator}`
            const datapoints = {};
            for(const time in response["Time Series (1min)"]){
                datapoints[new Date(time).getTime()] = response["Time Series (1min)"][time];
            }
            //console.log(datapoints)
            for(const time in datapoints){
                const nextMinute = Number(time) + 60 * 1000;
                if(!datapoints[nextMinute]) continue;
                const indicatorValue = Number(datapoints[time][indicatorKey]);
                const nextIndicatorValue = Number(datapoints[nextMinute][indicatorKey]);
                //console.log(indicatorValue, nextIndicatorValue)
                res[Number(time)] = action == "UP" ? 
                    Number(nextIndicatorValue / indicatorValue >= (1 + amount / 10000)) : 
                    Number(nextIndicatorValue / indicatorValue <= (1 - amount / 10000))
                ;
                /*console.log({
                    time : Number(time),
                    value : action == "UP" ? 
                        nextIndicatorValue / indicatorValue > (1 + amount / 10000) : 
                        nextIndicatorValue / indicatorValue < (1 - amount / 10000)
                }, datapoints[time], datapoints[nextMinute])*/
            }
            resolve({
                datapoints : res,
                type : "output"
            })
        }),1000)
    }
})

/*module.exports.getOutputData({
    type : `stock/high/DOWN/1`,
    label : `MSFT stock high DOWN-1`,
    value : `stock/MSFT/high/DOWN/1`
}).then(response => {
    console.log(response)
})*/
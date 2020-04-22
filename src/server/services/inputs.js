const fetchFromAPI = require("src/server/utility/alphavantageAPI")

const companies = ["MSFT", "SNE", "XIACF", "IBM"]
const companyStockIndicators = ["open", "high", "low", "close", "volume"]

module.exports.getInputs = () => {
    const res = []
    for(const company of companies){
        res.push({
            label : company,
            options : []
        })
        for(const indicator of companyStockIndicators){
            res[res.length-1].options.push({
                type : `stock/${indicator}`,
                label : `${company} stock ${indicator}`,
                value : `stock/${company}/${indicator}`
            })
        }
    }
    return res;
}

module.exports.getInputData = input => new Promise((resolve, reject) => {
    const type = input.type.split("/");
    const value = input.value.split("/");
    if(
        type.length == 2 &&
        type[0] == 'stock' &&
        companyStockIndicators.includes(type[1]) &&
        value.length == 3 &&
        companies.includes(value[1])
    ){
        const company = value[1];
        const indicator = value[2];
        fetchFromAPI({
            function : "TIME_SERIES_INTRADAY",
            symbol : company,
            interval : "1min",
            outputsize : "full"
        }).then(response => {
            const res = []
            const indicatorKey = `${companyStockIndicators.indexOf(indicator)+1}. ${indicator}`
            for(const time in response["Time Series (1min)"]){
                //console.log(time, response["Time Series (1min)"][time])
                res[new Date(time).getTime()] = Number(response["Time Series (1min)"][time][indicatorKey])
            }
            resolve({
                datapoints : res,
                type : "input"
            })
        })
    }
})

/*module.exports.getInputData({
    type : `stock/volume`,
    label : `MSFT stock volume`,
    value : `stock/MSFT/volume`
}).then((response) => {
    console.log(response)
})*/
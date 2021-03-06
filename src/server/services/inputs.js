const {fetchFromAPI, getURL} = require("src/server/utility/alphavantageAPI")

const companies = ["MSFT", "SNE", "XIACF", "IBM"]
const companyStockIndicators = ["open", "high", "low", "close", "volume"]

// generate all input options
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
    res.push({
        type : "difference",
        label : "difference",
        value : "difference"
    })
    return res;
}

// get input URL based on input object
module.exports.getAPIurlInput = input => {
    const type = input.type.split("/");
    const value = input.value.split("/");
    if(input.type == "difference"){
        return getURL({
            function : "TIME_SERIES_INTRADAY",
            symbol : "MSFT",
            interval : "1min",
            outputsize : "full"
        })
    }
    if(
        type.length == 2 &&
        type[0] == 'stock' &&
        companyStockIndicators.includes(type[1]) &&
        value.length == 3 &&
        companies.includes(value[1])
    ){
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

// fetch and format input data based on input object
module.exports.getInputData = input => new Promise((resolve, reject) => {
    const type = input.type.split("/");
    const value = input.value.split("/");
    if(input.type == "difference"){
        console.log("difference")
        fetchFromAPI({
            function : "TIME_SERIES_INTRADAY",
            symbol : "MSFT",
            interval : "1min",
            outputsize : "full"
        }).then(response => {
            const res = []
            const indicatorKey1 = `${companyStockIndicators.indexOf("open")+1}. ${"open"}`
            const indicatorKey2 = `${companyStockIndicators.indexOf("close")+1}. ${"close"}`
            for(const time in response["Time Series (1min)"]){
                res[new Date(time).getTime()] = Number(response["Time Series (1min)"][time][indicatorKey1]) - Number(response["Time Series (1min)"][time][indicatorKey2])
            }
            resolve({ 
                datapoints : res,
                type : "input"
            })
        })
    }
    else if(
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
                res[new Date(time).getTime()] = Number(response["Time Series (1min)"][time][indicatorKey])
            }
            resolve({
                datapoints : res,
                type : "input"
            })
        })
    }
})

// test function
/*module.exports.getInputData({
    type : `stock/volume`,
    label : `MSFT stock volume`,
    value : `stock/MSFT/volume`
}).then((response) => {
    console.log(response)
})*/
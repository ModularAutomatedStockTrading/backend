const companies = ["MSFT", "SNE", "XIACF", "IBM"]
const companyStockIndicators = ["open", "high", "low", "close", "volume"]
const indicatorActions = [
    "UP", "UP-1","UP-2", "UP-3","UP-4","UP-5", "UP-10","UP-15","UP-20", "UP-30", "UP-50", "UP-100", "UP-250", "UP-500", "UP-1000",
    "DOWN", "DOWN-1","DOWN-2", "DOWN-3","DOWN-4","DOWN-5", "DOWN-10","DOWN-15","DOWN-20", "DOWN-30", "DOWN-50", "DOWN-100", "DOWN-250", "DOWN-500", "DOWN-1000",
];

module.exports.getOutputs = () => {
    const res = []
    for(const company of companies){
        const companyOptions = []
        for(const indicator of companyStockIndicators){
            const indicatorOptions = []
            for(const action of indicatorActions){
                companyOptions.push({
                    type : `stock/${indicator}/${action}`,
                    label : `${company} stock ${indicator} ${action}`,
                    value : `stock/${company}/${indicator}/${action}`
                })
            }
        }
        res.push({
            label : company,
            options : companyOptions
        })
    }
    return res;
}
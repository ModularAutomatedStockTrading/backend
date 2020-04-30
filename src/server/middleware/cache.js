const ExternalCacheResponse = require("src/server/schema/ExternalCacheResponse").ExternalCacheResponse;

const fetchExternal = (url, func) => {
    return new Promise((resolve, reject) => {
        ExternalCacheResponse.findOne({
            url
        }).then(existingFetchData => {
            //console.log(existingFetchData, url)
            if(existingFetchData){
                resolve(
                    JSON.parse(
                        existingFetchData.data
                    )
                )
            }else{
                func().then(res => {
                    externalCacheResponse = new ExternalCacheResponse({
                        data : JSON.stringify(res),
                        url
                    });
                    externalCacheResponse.save().then(() => {
                        resolve(res);
                    });
                })
            }
        })
    })
}

module.exports = {
    fetchExternal
}
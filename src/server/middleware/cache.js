const ExternalCacheResponse = require("src/server/schema/ExternalCacheResponse").ExternalCacheResponse;

const fetchExternal = (url, func) => {
    return new Promise((resolve, reject) => {
        ExternalCacheResponse.findOne({
            url
        }).then(existingFetchData => {
            if(existingFetchData && existingFetchData.hasFetched){
                console.log("cachelog: got previously fetched data")
                resolve(
                    JSON.parse(
                        existingFetchData.data
                    )
                )
            }else if(existingFetchData){
                ExternalCacheResponse.watch().on("change", query => {
                    //console.log(query, existingFetchData, query.operationType, query.documentKey._id, existingFetchData._id)
                    //console.log(query.operationType == "update" && query.documentKey._id == existingFetchData._id, query.operationType == "update", query.documentKey._id, existingFetchData._id, query.documentKey._id === existingFetchData._id)
                    if(
                        query.operationType == "update" &&
                        JSON.stringify(query.documentKey._id) == JSON.stringify(existingFetchData._id)
                    ){
                        console.log("cachelog: got existing fetch that was fetching")
                        resolve(
                            JSON.parse(
                                query.updateDescription.updatedFields.data
                            )
                        )
                    }
                })
            }else{
                const externalCacheResponse = new ExternalCacheResponse({
                    url
                });
                externalCacheResponse.save();
                func().then(res => {
                    ExternalCacheResponse.findOneAndUpdate({url}, {
                        data : JSON.stringify(res),
                        hasFetched : true
                    }).then((response) => {
                        console.log("cachelog: made new fetch")
                        resolve(res)
                    });
                })
            }
        })
    })
}

module.exports = {
    fetchExternal
}
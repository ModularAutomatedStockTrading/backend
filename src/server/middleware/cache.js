const ExternalCacheResponse = require("src/server/schema/ExternalCacheResponse").ExternalCacheResponse;

const fetchExternal = (url, func) => {
    console.start("CACHELOG")
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
                console.stop()
            }else if(existingFetchData){
                ExternalCacheResponse.watch().on("change", query => {
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
                        console.stop()
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
                        console.stop()
                    });
                })
            }
        })
    })
}

module.exports = {
    fetchExternal
}
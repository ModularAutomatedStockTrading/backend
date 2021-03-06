const ExternalCacheResponse = require("src/server/schema/ExternalCacheResponse").ExternalCacheResponse;

// check the database for the data received from fetching thr url. Otherwise fetches a new request response.
const fetchExternal = (url, func) => {
    console.start("CACHELOG")
    console.log(url)
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
                /*const changeStream = ExternalCacheResponse.watch().on("change", query => {
                    if(
                        query.operationType == "update" &&
                        JSON.stringify(query.documentKey._id) == JSON.stringify(existingFetchData._id)
                    ){
                        console.log("cachelog: got existing fetch that was fetching")
                        changeStream.close();
                        resolve(
                            JSON.parse(
                                query.updateDescription.updatedFields.data
                            )
                        )
                        console.stop()
                    }
                })*/
                setTimeout(() => { // hacky
                    ExternalCacheResponse.findOne({
                        url
                    }).then(existingFetchData => {
                        resolve(
                            JSON.parse(
                                existingFetchData.data
                            )
                        )
                    })
                }, 5000)
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
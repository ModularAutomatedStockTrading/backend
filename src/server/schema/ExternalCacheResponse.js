const mongoose = require("mongoose");

const Schema = require('mongoose').Schema;

const struct = new Schema({
    data : String,
    url : String,
    createdAt: {
        type: Date,
        default: Date.now(),
        index : {
            expires : 60
        }
    }
});

/*struct.index({
    createdAt : 1
}, {expireAfterSeconds: 10})*/


module.exports.ExternalCacheResponse = mongoose.model('ExternalCacheResponse', struct);

module.exports.ExternalCacheResponse.on('index', function(error) {console.log("wdnjwndwjd")});
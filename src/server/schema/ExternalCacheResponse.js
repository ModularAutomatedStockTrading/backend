const mongoose = require("mongoose");
mongoose.set('useCreateIndex', true);
const Schema = require('mongoose').Schema;

const struct = new Schema({
    data : String,
    url : String,
    hasFetched : {
        type : Boolean,
        default : false
    },
    createdAt: {
        type: Date,
        default: Date.now
    }
});
struct.index({
    createdAt : 1
}, {expireAfterSeconds: 60})

const model = mongoose.model('ExternalCacheResponse', struct);;

module.exports.ExternalCacheResponse = model;

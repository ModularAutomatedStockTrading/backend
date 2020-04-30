const mongoose = require("mongoose");
mongoose.set('useCreateIndex', true);
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
struct.index({ url: 1 });
const model = mongoose.model('ExternalCacheResponse', struct);;
model.on('index', function(error) {console.log("wdnjwndwjd")});

module.exports.ExternalCacheResponse = model;

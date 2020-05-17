const express = require("express");
const {getInputs} = require("src/server/services/inputs");
const {getOutputs} = require("src/server/services/outputs");
const {fetchFromAPI} = require("src/server/utility/alphavantageAPI")
const router = express.Router();

// test call
router.use("/trade", async (req, res) => {
    const config = {
        function : "TIME_SERIES_INTRADAY",
        symbol : "MSFT",
        interval : "1min"
    };
    const data = await fetchFromAPI(config);
    res.send(data);
})

// handler for getting all input options
router.get("/inputs", (req, res) => {
    res.send({inputs : getInputs()})
})

// handler for getting all output options
router.get("/outputs", (req, res) => {
    res.send({outputs : getOutputs()})
})

module.exports = router;
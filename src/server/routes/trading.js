const express = require("express");
const fetchFromAPI = require("server/utility/alphavantageAPI")
const router = express.Router();

router.use("/trade", async (req, res) => {
    const config = {
        function : "TIME_SERIES_INTRADAY",
        symbol : "MSFT",
        interval : "1min"
    };
    const data = await fetchFromAPI(config);
    res.send(data);
})


module.exports = router;
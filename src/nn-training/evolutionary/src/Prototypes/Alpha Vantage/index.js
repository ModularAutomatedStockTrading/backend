const express = require('express');
const fetch = require('node-fetch');
var fs = require('fs');
const app = express();
app.listen(3000, () => console.log('listening at 3000'));
app.use(express.static('public'));
app.use(express.json());

app.get('/stock/:StockSymbol/:API_KEY', async (request, response) => {
    const API_KEY = request.params.API_KEY;
    const StockSymbol = request.params.StockSymbol;
    console.log(API_KEY, StockSymbol);
    const API_Call = `https://www.alphavantage.co/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol=${StockSymbol}&outputsize=compact&apikey=${API_KEY}`;
    //const API_Call = `https://www.alphavantage.co/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol=${StockSymbol}&outputsize=full&apikey=${API_KEY}`;
    const fetch_response = await fetch(API_Call);
    const data = await fetch_response.json();
    var json = JSON.stringify(data);
    fs.writeFileSync('stock.json', json);
    response.json(data);
});
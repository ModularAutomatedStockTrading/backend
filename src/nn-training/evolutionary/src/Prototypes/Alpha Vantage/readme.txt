change value of StockSymbol in index.html to the tickercode you want:

clear stock.json
save stock.json

if full history is wantet switch out the API_Call in index.js

to start server:
cd to source folder e.g:
type in cmd:
cd C:\Users\Asmus\Desktop\sukkertoppen\DDU\aktier\GET DAT JSON\v1
hit enter

type in cmd:
node index.js
hit enter

should repond "listening at 3000"

open browser
go to url localhost:3000

check stock.json

if no change refresh the browser and look again or try killing the server and starting it again

press ctrl+c in cmd to kill server
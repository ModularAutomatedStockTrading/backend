FROM node:13.13.0
WORKDIR /usr/app
COPY . .
RUN apt-get install g++
RUN npm install
EXPOSE 4000
RUN npm run compile
CMD ["npm", "run", "start-linux-prod"]

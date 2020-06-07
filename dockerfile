FROM node:13.13.0
WORKDIR /usr/app
COPY . .
RUN apt-get install g++
RUN npm install
EXPOSE 4000
RUN chmod +x run.bash
RUN chmod +x compile.bash
CMD ["npm", "run", "start-linux-prod"]

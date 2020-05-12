FROM node:14.2.0
WORKDIR /usr/app
COPY . .
RUN apt-get install g++
RUN npm run install
EXPOSE 4000
RUN chmod +x run.bash
CMD ["./run.bash"]
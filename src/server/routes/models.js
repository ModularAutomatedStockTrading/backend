const express = require("express");
const Model = require("server/schema/model").model;
const ModelTemplate = require("server/schema/modelTemplate").model;
const router = express.Router();
const ModelService = require("server/services/model")

router.post("/", async (req, res) => {
    const modelTemplateID = req.body.data.modelTemplateID;
    const modelTemplate = (await ModelTemplate.findById(modelTemplateID)).toObject();
    delete modelTemplate._id;
    const model = new Model({
        ...modelTemplate,
        name : req.body.data.name,
        description : req.body.data.description
    });
    model.save();
    res.send({model});
});

router.get("/", async (req, res) => {
    const models = await Model.find();
    res.send({models});
});

router.patch("/:id", async (req, res) => {
    const model = await Model.findByIdAndUpdate(req.params.id, req.body.data, {new : true});
    res.send({model});
});

router.delete("/:id", async (req, res) => {
    await Model.findByIdAndDelete(req.params.id);
    res.sendStatus(200);
});

router.post("/:id/train", async (req, res) => {
    const model = await Model.findById(req.params.id);
    
    model.isTraining = true;
    model.save();

    res.sendStatus({model});
    
    const modelService = new ModelService(model);
    //modelService.train();
    //const res = modelService.getResult();
    
    model.hasTrained = true;
    model.isTraining = false;
    model.save();
})

module.exports = router;
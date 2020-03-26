const express = require("express");
const Model = require("server/schema/model").model;
const ModelTemplate = require("server/schema/modelTemplate").model;
const router = express.Router();

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
    //await 
})

module.exports = router;
const Note=require('../models/Note');
const User=require('../models/User');

const addNote=async(req,res)=>{
    console.log('here');
    
    try{
        const {title,content}=req.body;
        const {userId}=req.params;

        const newNote=new Note({
            title,
            content,
            user: userId,
            lastModified: new Date().toISOString()
        });

        await newNote.save();
        res.status(201).json({message:'Note added successfully',note:newNote});
    }catch(err){
        console.error('Error adding note:', err);
        res.status(500).json({message:'Server error while adding note'});
    }
}
module.exports={addNote};
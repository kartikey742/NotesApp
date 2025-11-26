const Note=require('../models/Note');
const User=require('../models/User');
const mongoose=require('mongoose');
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
const getNotes=async(req,res)=>{
     try {
     
    const { userId } = req.params;
       const userObjectId = new mongoose.Types.ObjectId(userId);

    const notes = await Note.find({ user: userObjectId });
    console.log('notes');
     
    res.json(notes);
  } catch (err) {
    console.log(err);
    
    res.status(500).json({ message: "Server error" });
  }}
 const updateNote=async(req,res)=>{
    try{
        const {noteId}=req.params;
        const {title,content}=req.body;

        const updatedNote=await Note.findByIdAndUpdate(noteId,{
            title,
            content,
            lastModified: new Date().toISOString()
        },{new:true});

        res.json({message:'Note updated successfully',note:updatedNote});
    }catch(err){
        console.error('Error updating note:', err);
        res.status(500).json({message:'Server error while updating note'});
    }
}
const deleteNote=async(req,res)=>{
    try{
        const {noteId}=req.params;
        await Note.findByIdAndDelete(noteId);
        res.json({message:'Note deleted successfully',success:true,jk:'gh'});
    }catch(err){
        console.error('Error deleting note:', err);
        res.status(500).json({message:'Server error while deleting note'});
    }
}
module.exports={addNote,getNotes,updateNote,deleteNote};
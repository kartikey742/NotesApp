import React, { use, useState } from 'react';
import '../css/Modal.css';
import { toast } from 'react-toastify';
import { useEffect } from 'react';
export const Modal = ({ open, setOpen,setNotesData,notesData, noteData, setEditMode, editMode }) => {
  const [title, setTitle] = useState('');
  const [content, setContent] = useState('');
  useEffect(() => {
    if (editMode) {
      setTitle(noteData.title);
      setContent(noteData.content);
    }
  }, [editMode, noteData]);

  const handleSubmit = async (e) => {
    e.preventDefault();
    if (!title.trim() || !content.trim()) return toast.error('Please fill out both fields.');
    const user = JSON.parse(localStorage.getItem('user'));
    const userId = user ? user._id : null;
    if (!userId) return toast.error('User not found. Please log in again.');
    const newNote = {
      title,
      content,
      lastModified: new Date().toISOString(),
    };
    const token = localStorage.getItem('token');
    let res
    if(!editMode){
   res=await fetch(`http://localhost:4000/api/notes/add-note/${userId}`,{
    method:'POST',
    headers:{'Content-Type':'application/json',
  "Authorization": `Bearer ${token}`
    },
    body:JSON.stringify(newNote)
  });
}
else{
   res=await fetch(`http://localhost:4000/api/notes/update-note/${noteData._id}`,{
    method:'PUT',
    headers:{'Content-Type':'application/json',
  "Authorization": `Bearer ${token}`
    },
    body:JSON.stringify(newNote)
  });
}
  const data=await res.json();
  console.log(data);
  if(!res.ok){
    return toast.error(data.message || 'Failed to add note.');
  }
    setTitle('');
    setContent('');
    setOpen(false);
    if(editMode){
      const updatedNotes = notesData.map((note) =>
        note._id === data.note._id ? data.note : note
      );
      setNotesData(updatedNotes);
      toast.success('Note updated successfully!');
      setEditMode(false);
    }else{
      setNotesData([...notesData, data.note]);
      toast.success('Note added successfully!');
    }
  }
  return (
    <form className="add-note-form" onSubmit={handleSubmit}>
      <input
        type="text"
        className="note-title-input"
        placeholder="Enter title..."
        value={title}
        onChange={(e) => setTitle(e.target.value)}
      />
      <textarea
        className="note-content-input"
        placeholder="Write your note..."
        rows="6"
        value={content}
        onChange={(e) => setContent(e.target.value)}
      ></textarea>
      <button type="submit" className="save-btn">Save Note</button>
      <button type="button" className="cnc-btn" onClick={() => {setOpen(false); setEditMode(false); setContent(''); setTitle('');}}>Cancel</button>
    </form>
  );
};

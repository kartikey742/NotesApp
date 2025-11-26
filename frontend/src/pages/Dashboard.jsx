import React, { useEffect } from 'react'
import '../css/dashboard.css'
import { IoAdd } from 'react-icons/io5';
import { useState } from 'react';
import {Modal} from '../modals/Modal';
import { Logout } from './Logout';
import Navbar from './Navbar';
export const Dashboard = () => {
  const [notesData,setNotesData]=useState([]);
  const [noteData,setNoteData]=useState({});
  const [editMode,setEditMode]=useState(false);
  const user = JSON.parse(localStorage.getItem('user'));
  const userId = user ? user._id : null;
  const token = localStorage.getItem('token');

  
useEffect(()=>{
  const fetchNotes = async () => {
  const res = await fetch(`${process.env.REACT_APP_API_URL}/notes/get-notes/${userId}`, {
    method: 'GET',
    headers: {
      'Content-Type': 'application/json',
      'Authorization': `Bearer ${token}`,
    },
  });
  const data=await res.json();
  console.log(data);
  setNotesData(data)
}
fetchNotes();
},[userId])
const onDelete = async (noteId) => {
  try {
    const res = await fetch(`${process.env.REACT_APP_API_URL}/notes/delete-note/${noteId}`, {
      method: 'DELETE',
      headers: {
        'Content-Type': 'application/json',
        'Authorization': `Bearer ${token}`
      }
    });
    const data = await res.json();
    console.log(data);
    setNotesData(prevNotes => prevNotes.filter(note => note._id !== noteId));
  } catch (error) {
    console.error("Error deleting note:", error);
  }
};

const [open, setOpen] = useState(false);

  return (
    <><Navbar/>
  <div className={`notes-container ${open ? "active" : ""}`}>
        

        {notesData?.map((note) => (
          <div key={note.id} className="note-card">
            <h2 className="note-title">{note.title}</h2>
            <p className="note-content">{note.content}</p>
            <button className='dlt-btn' onClick={() => onDelete(note._id)}>delete</button>
            <button className='edt-btn'  onClick={() => {setNoteData(note);setOpen(true); setEditMode(true);}}>edit</button>
          </div>
        ))}
        <div>

        <button className='add' onClick={() => setOpen(true)}><IoAdd /></button>
        </div> 
        {open && <div className="modal-overlay"><Modal open={open} setOpen={setOpen} setNotesData={setNotesData} notesData={notesData} noteData={noteData} setEditMode={setEditMode} editMode={editMode} /></div>}
      </div>
      </>
  )
}

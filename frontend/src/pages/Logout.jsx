import React from 'react'
import { useNavigate } from 'react-router-dom';
export const Logout = () => {
    const navigate = useNavigate();
    const logout=()=>{
        localStorage.removeItem('user');
        localStorage.removeItem('token');
        navigate('/login');
       
    }
  return (
    
        <button className='logout-btn' onClick={logout}>Logout</button>
    
  )
}

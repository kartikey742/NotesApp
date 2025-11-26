import React, { Children } from 'react'
import { useLocation, Navigate } from 'react-router-dom';
export const CheckAuth = ({children}) => {
  const { pathname } = useLocation();
  if (pathname === '/dashboard' && !localStorage.getItem('token')) {
    
    return <Navigate to="/login" />
  }
 if ((pathname === '/login' || pathname === '/signup') && localStorage.getItem('token')) {
    return <Navigate to="/dashboard" />
  }
  else 
    return children
}

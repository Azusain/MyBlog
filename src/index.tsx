import React from 'react';
import ReactDOM from 'react-dom/client';
// Official React-Router APIs has been updated
// deprecented APIs are listed in: https://reactrouter.com/en/main/routers/picking-a-router
import {
    createBrowserRouter, 
    RouterProvider
} from 'react-router-dom';


// customized components
import Header from './components/Header';
import Display from './components/Display';
import Work from './components/Work';
import Blog from './components/Blog';
import Footer from './components/Footer';

// Pages
import BlogsPage from './BlogsPage';
import ContactPage from './ContactPage';

const HomePage: React.FC = () => {
    return (
        <>
        <Header />
        <Display></Display>
        <Blog></Blog>
        <Work></Work>
        <Footer></Footer>
        </>
    )
}

// Global router
const router = createBrowserRouter([
    {
        path: "/",
        element: <HomePage/>,
    },
    {
        path: "/blogs",
        element: <BlogsPage/>,
    },
    {
        path: "/contact",
        element: <ContactPage/>,
    }
]);


ReactDOM.createRoot(document.getElementById('root') as HTMLElement).render(
//   <React.StrictMode>
    
//   </React.StrictMode>
    <RouterProvider router={router}></RouterProvider>
);




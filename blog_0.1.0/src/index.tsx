import React from 'react';
import ReactDOM from 'react-dom/client';
// Official React-Router APIs has been updated
// deprecented APIs are listed in: https://reactrouter.com/en/main/routers/picking-a-router
import {
    createHashRouter, 
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
import PassagePage from './PassagePage';

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
const router = createHashRouter([{
        path: "/",
        element: <HomePage/>,
    }, {
        path: "/blogs",
        element: <BlogsPage/>,
    }, {
        path: "/contact",
        element: <ContactPage/>,
    }, {
        path: "/passage",
        element: <PassagePage/>
    }
]);

ReactDOM.createRoot(document.getElementById('root') as HTMLElement).render(
//   <React.StrictMode>
    
//   </React.StrictMode>
    <RouterProvider router={router}></RouterProvider>
);




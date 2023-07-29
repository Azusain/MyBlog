import React from 'react';
import ReactDOM from 'react-dom/client';



// customized components
import Header from './Header';
import Display from './Display';
import Work from './Work';
import Blog from './Blog';
import Footer from './Footer';


const root = ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
);


const HomePage: React.FC = () => {
    return (
        <>
        <Header />
        <Display></Display>
        <Work></Work>
        <Blog></Blog>
        <Footer></Footer>
        </>
    )
}







root.render(
  <React.StrictMode>

  </React.StrictMode>
);




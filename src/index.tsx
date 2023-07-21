import React from 'react';
import ReactDOM from 'react-dom/client';

import Header from './Header';
import Display from './Display';
import Work from './Work';

import ImageWithDetails from './components/ImageWithDetails';

const root = ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
);
root.render(
  <React.StrictMode>
    <Header />
    <Display></Display>
    <Work></Work>
    <ImageWithDetails></ImageWithDetails>
  </React.StrictMode>
);




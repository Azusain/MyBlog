import React from 'react'
import GuraButton from './GuraButton';
import img0 from '../img/blog-1.jpg'


interface PassageStatusLineInterface {
    owner?: string;
    date?: string;
    commentsN?: number;
    children?: React.ReactNode;
}


const ImageWithDetails: React.FC = () => {
    return (
        <div>
            <h2>Design</h2>
            <img alt='' src={img0}></img>
            <PassageStatusLine></PassageStatusLine>
            <h3>descriptions...</h3>
            <GuraButton text='Read More'/>
        </div>
    )
}

const PassageStatusLine: React.FC<PassageStatusLineInterface> = (props) => {
    return (
        <div className="flex flex-row w-full justify-between">
            <div className="divide-x flex flex-row">
                <div>2020-1-21</div>
                <div>Admin</div>
            </div>
            <div>7 Comnents</div>
        </div>
    )
}


export default ImageWithDetails;
export {PassageStatusLine};
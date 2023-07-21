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
        <div className="bg-slate-100 w-1/6">
            <h2 className="text-gura_main">Design</h2>
            <img alt='' src={img0}></img>
            <PassageStatusLine></PassageStatusLine>
            <h3>descriptions...</h3>
            <GuraButton/>
        </div>
    )
}

const PassageStatusLine: React.FC<PassageStatusLineInterface> = (props) => {
    return (
        <div className="flex flex-row w-full bg-amber-100 justify-between">
            <div className="divide-x flex flex-row divide-black">
                <div>2020-1-21</div>
                <div>Admin</div>
            </div>
            <div>7 Comnents</div>
        </div>
    )
}


export default ImageWithDetails;
export {PassageStatusLine};
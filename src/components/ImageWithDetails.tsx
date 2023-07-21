import React from 'react'

interface PassageStatusLineInterface {
    owner?: string;
    date?: string;
    commentsN?: number;
    children?: React.ReactNode;
}


const ImageWithDetails: React.FC = () => {
    return (
        <div className="bg-slate-600">
            <h2>From Blog</h2>
            <PassageStatusLine></PassageStatusLine>
            <h3>I am subtitles</h3>
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
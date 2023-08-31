import React from 'react'
import GuraButton from './GuraButton';
import img0 from '../img/blog-1.jpg'
import { useNavigate } from 'react-router-dom';


interface PassageStatusLineInterface {
    owner?: string;
    date?: string;
    commentsN?: number;
    children?: React.ReactNode;
}

interface BlogItemInterface {
    hasImage: boolean
    img?: string
    brief: string
    date?: string
    title: string
    topic?: string
}

interface BlogTopicItemInterface extends BlogItemInterface {
    passages?: Array<BlogItemInterface>
}

const ImageWithDetails: React.FC = () => {
    return (
        <div>
            <h3>Design</h3>
            <img alt='' src={img0} className='shadow-lg'></img>
            <PassageStatusLine />
            <h6>descriptions...</h6>
            <GuraButton text='Read More' />
        </div>
    )
}

const BlogTopicItem: React.FC<BlogTopicItemInterface> = (props) => {
    return (
        <div>
            <div className='flex flex-col gap-2 p-2'>
                <h3><u>{props.title}</u></h3>
                <PassageStatusLine date={props.date} />
                <img
                    alt=''
                    src={img0}
                    className={props.hasImage ? '' : 'hidden'}
                >
                </img>
                <h6>{props.brief}</h6>
                <div className={props.hasImage ? '' : 'hidden'}>
                    {props.passages && (<GuraButton text='Read More' />)}
                </div>
            </div>
        </div>
    )
}

const BlogItem: React.FC<BlogItemInterface> = (props) => {
    let navi = useNavigate()
    return (
        <div>
            <div className='flex flex-row gap-2'>
                <div className='basis-2/5 pt-[1.15rem]'>
                    <img
                        alt=''
                        src={img0}
                        className={`${props.hasImage ?  '': 'hidden'} shadow-lg`}
                    >
                    </img>
                </div>
                <div className='basis-3/5 flex flex-col gap-2 p-2'>
                    <h3
                        className="blog-item-title"
                        onClick={() => {
                            navi(`/passage?topic=${props.topic}&title=${props.title}`)
                        }}
                    ><u>{props.title.replace(".html", "").replaceAll("-", " ").replaceAll("_", "-")}</u></h3>
                    <PassageStatusLine date={props.date} />
                    <h6>{props.brief}</h6>
                </div>
            </div>
        </div>
    )
}

const PassageStatusLine: React.FC<PassageStatusLineInterface> = (props) => {
    return (
        <div className="flex flex-row w-full justify-between">
            <div className="flex flex-row gap-2">
                <div>{props.date ? props.date : "2023/8/31"}</div>
                <div className='text-gura_main'>Admin</div>
            </div>
        </div>
    )
}

export default ImageWithDetails;
export { PassageStatusLine, BlogTopicItem, BlogItem };
export type { BlogItemInterface, BlogTopicItemInterface }
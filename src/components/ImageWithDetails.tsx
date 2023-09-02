import React, { useState } from 'react'
// customized component
import GuraButton from './GuraButton';
import img0 from '../img/map.jpg'
import { useNavigate } from 'react-router-dom';
import { getTopicData } from '../api/passages';
import src_rt_path from '../api/media';

interface ImageWithDetailsInterface {
    topic: string
}

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

// @todo: customized size!!!!
const ImageWithDetails: React.FC<ImageWithDetailsInterface> = (props) => {
    const [topicData, setTopicData] = useState<BlogTopicItemInterface>()
    let navi = useNavigate()

    function afterFetch(data: BlogTopicItemInterface) { // call back func for fetch api 
        setTopicData(data)
    }

    // check session storage before deciding to fetch data from server
    var topicDataLocal = sessionStorage.getItem(props.topic)
    var topicDataObj: BlogTopicItemInterface = {
        hasImage: false,
        brief: "",
        title: "",
    };
    if(!topicDataLocal) {
        getTopicData(afterFetch, props.topic)
    } else {
        topicDataObj = JSON.parse(topicDataLocal)
    }

    // @todo: wrap string with css
    if(topicDataObj) {
        return (
            <div>
                <h3>{topicDataObj.title}</h3>
                <div className='p-2'>
                    <img 
                        alt='' 
                        src={`${src_rt_path}/${props.topic}/${props.topic}.png`} 
                        className='shadow-lg mb-2 w-64 h-36'
                    ></img>
                    <PassageStatusLine date={topicDataObj.date} />
                    <h6 className='h-20 w-64'>{`${topicDataObj.brief.substring(0, 100)} ...`}</h6>      
                    <GuraButton text='Read More' onClick={() => {
                        navi(`/blogs?topic=${topicDataObj.title}`)
                    }} />
                </div>
            </div>
        )
    } else {
        return (<></>)
    }
}

const BlogTopicItem: React.FC<BlogTopicItemInterface> = (props) => {
    return (
        <div>
            <div className='flex flex-col gap-2 p-2'>
                <h3><u>{props.title}</u></h3>
                <PassageStatusLine date={props.date} />
                <img
                    alt=''
                    src={`${src_rt_path}/${props.title}/${props.title}.png`}
                    className={`w-[38rem] h-[19rem] ${props.hasImage ? '' : 'hidden'}`}
                >
                </img>
                <h6 className="w-[38rem]">{props.brief}</h6>
                <div>
                    <GuraButton text='Read More' onClick={() => {
                        alert('戳文章标题别戳我')
                    }} />
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
                {props.hasImage && (
                    <div className='basis-2/5 pt-[1.15rem]'>
                        <img
                            alt=''
                            src={img0}
                            className={`shadow-lg`}
                        >
                        </img>
                    </div>
                )}
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
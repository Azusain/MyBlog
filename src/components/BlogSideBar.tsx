import { BlogTopicItemInterface } from "./ImageWithDetails"
import '../output.css'
import { useNavigate } from "react-router-dom"

interface SideBarInterface { 
    column: string
    curPsg: string
}  

const BlogSideBar: React.FC<SideBarInterface> = (props) => {
    const topicData = JSON.parse(sessionStorage.getItem(props.column) as string)
    let navi = useNavigate()
    return (
        <div className="p-4 border-r-2 h-full">
            <h3>{topicData.title}</h3>
            <ul className="flex flex-col gap-2 mt-2">
                {
                    topicData.passages.map((val: BlogTopicItemInterface, idx: number) => {
                        return (
                        <li 
                            key={idx}
                            className={`sidebar-item ${props.curPsg === val.title ? "text-gura_main": ""}`}
                            onClick={() => {
                                navi(`/passage?topic=${topicData.title}&title=${val.title}`)
                            }}
                        >{val.title.replace(".html", "")}</li>)
                    })
                }
            </ul> 
        </div>
    )
}


export default BlogSideBar;
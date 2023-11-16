import { useSearchParams } from "react-router-dom";
import Footer from "./components/Footer";
import Header from "./components/Header";
import BlogSideBar from "./components/BlogSideBar";
import src_rt_path from "./api/media";

const PassagePage: React.FC = () => {
    const [params, setParams] = useSearchParams()
    var cur_topic = params.get("topic")
    var cur_psg = params.get("title")
    return (
        <div>
            <Header/>
            {/* Main */}
            <div className="h-full flex flex-row">
                {/* sidebar */}
                <div className="basis-1/6 ">
                    <BlogSideBar column={cur_topic as string} curPsg={cur_psg as string} />
                </div>
                {/* passage area */}
                <iframe 
                    title="passage"
                    className="w-full basis-5/6"
                    height="1560px"
                    src={`${src_rt_path}/${cur_topic}/${cur_psg}`}
                    // scrolling="no" // @todo: scrolling?
                >
                </iframe>
            </div>
        </div>
    )
}

export default PassagePage;
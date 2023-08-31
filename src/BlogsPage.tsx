import { useEffect, useState } from "react";
// customized components
import Footer from "./components/Footer";
import Header from "./components/Header";
import MainCon from "./components/MainCon";
import SearchBar from "./components/SearchBar";
import { BlogTopicItem, BlogItem } from "./components/ImageWithDetails";
import Collapse from "./components/Collapse";
import { BlogTopicItemInterface } from "./components/ImageWithDetails";
import getColumns from "./api/passages";
//  style sheet
import './output.css'
const BlogsPage: React.FC = () => {
    const [columns, setColumns] = useState<string[]>([]);
    const [topicData, setTopicData] = useState<BlogTopicItemInterface>()

    function passagesHandller(data: BlogTopicItemInterface) { // any, in typescript?
        setTopicData(data)
    }

    useEffect(() => {
        getColumns(setColumns);
    }, [])

    return (
        <>
            <Header />
            <MainCon width="46%" height="80rem" inner_layout="flex flex-row gap-8">
                <div className="basis-2/3 w-full">
                    <div className="flex flex-col divide-y gap-4">
                        {!topicData && (
                            <BlogTopicItem
                                hasImage={true}
                                title={"Welcome to My Blog!"}
                                brief={"head to Categories on the right side"}
                                date={"2023-8-31"}
                            ></BlogTopicItem>
                        )
                        }
                        {topicData && (
                            <BlogTopicItem
                                hasImage={true}
                                title={topicData.title}
                                brief={topicData.brief}
                                date={topicData.date}
                                passages={topicData.passages}
                            ></BlogTopicItem>
                        )}
                        {topicData && (topicData.passages!.map((val, idx) => {
                            return (<BlogItem
                                key={idx}
                                hasImage={true}
                                title={val.title}
                                brief={val.brief}
                                date={val.date}
                                topic={topicData.title}
                            ></BlogItem>)
                        }))}
                    </div>
                </div>

                <div className="basis-1/3 h-[30rem] flex flex-col gap-4 mt-4 ml-20">
                    <h3 className="font-bold">Search</h3>
                    <SearchBar></SearchBar>
                    <h3 className="font-bold">Categories</h3>
                    <div className="flex flex-col gap-2">
                        <Collapse
                            topic="Programming"
                            isCollapsed={true}
                            columns={columns}
                            handler={passagesHandller}
                        >
                        </Collapse>
                    </div>
                </div>
            </MainCon>

            <Footer></Footer>
        </>
    )
}

export default BlogsPage;

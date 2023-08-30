import Footer from "./components/Footer";
import Header from "./components/Header";
import MainCon from "./components/MainCon";

import SearchBar from "./components/SearchBar";
import { BlogItem, BlogItemBeta} from "./components/ImageWithDetails";
import Collapse from "./components/Collapse";

import './output.css'
import { useEffect, useState } from "react";

var backend_addr_4 = "http://localhost:5001"

const BlogsPage: React.FC = () => {
    const [columns, setColumns] = useState<string[]>([]);
    const [data, setData] = useState<any>()

    function passagesHandller(data: any) { // any, in typescript?
        console.log('triggered')
        console.log(data.brief)
        // setData(data)
    }


    useEffect(() => {
        fetch(
            `${backend_addr_4}/columns`, {
                method: "POST",
            }
        )
        .then((resp) => resp.json())
        .then((json) => {
            var tmp_arr = []
            for(let i = 0; i < json["columns"].length; ++i) {
                tmp_arr.push(json["columns"][i]) 
            }
            setColumns(tmp_arr)
        })
    }, [])


    return (
        <>
            <Header/>
            <MainCon width="46%" height="80rem" inner_layout="flex flex-row gap-8">
                <div className="basis-2/3 w-full">
                    <div className="flex flex-col divide-y gap-4">
                        <BlogItem isNews={true}></BlogItem>
                        <BlogItemBeta isNews={true}></BlogItemBeta>
                        <BlogItemBeta isNews={true}></BlogItemBeta>
                        <BlogItemBeta isNews={true}></BlogItemBeta>
                        <BlogItemBeta isNews={true}></BlogItemBeta>
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
export {backend_addr_4};
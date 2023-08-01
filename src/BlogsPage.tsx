import Footer from "./components/Footer";
import Header from "./components/Header";
import MainCon from "./components/MainCon";

import SearchBar from "./components/SearchBar";
import { BlogItem } from "./components/ImageWithDetails";
import Pagination from "./components/Pagination";

import './output.css'

const BlogsPage: React.FC = () => {
    return (        
        <>
            <Header/>
            <MainCon width="46%" height="80rem" inner_layout="flex flex-row gap-8">
                <div className="basis-2/3 w-full">
                    <div className="flex flex-col divide-y gap-4">
                        <BlogItem isNews={true}></BlogItem>
                        <BlogItem isNews={false}></BlogItem>
                        <BlogItem isNews={false}></BlogItem>
                        <BlogItem isNews={false}></BlogItem>
                    </div>

                </div>
                
                <div className="basis-1/3 h-[30rem] flex flex-col gap-4 mt-4">
                    <h3 className="font-bold">Search</h3>
                    <SearchBar></SearchBar>
                    <h3 className="font-bold">Categories</h3>
                    
                    <div className="flex flex-col gap-2">
                        <div>》 Computer System</div>
                        <div>》Algorithm</div>
                        <div>》AI</div>
                        <div>》Unreal Engine</div>
                    </div>

                    

                </div>
 
            </MainCon>
            
            <Footer></Footer>
        </>
    )
}

export default BlogsPage;
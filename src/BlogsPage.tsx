import Footer from "./components/Footer";
import Header from "./components/Header";
import MainCon from "./components/MainCon";
import SearchBar from "./components/SearchBar";
import './output.css'

const BlogsPage: React.FC = () => {
    return (        
        <>
            <Header/>
            <MainCon width="46%" height="80rem" inner_layout="flex flex-row">
                <div className="basis-2/3 bg-slate-500 h-[50rem] w-full">
                    3434

                </div>
                <div className="basis-1/3 bg-slate-700 h-[30rem]">
                    <h3>Search</h3>
                    <SearchBar></SearchBar>
                    <h3>Categories</h3>
                    <div className="flex flex-col gap-2">
                        <div className="bg-orange-500">Computer System</div>
                        <div className="bg-orange-500">Algorithm</div>
                        <div className="bg-orange-500">AI</div>
                        <div className="bg-orange-500">Unreal Engine</div>
                    </div>
                </div>
 
            </MainCon>
            
            {/* <Footer></Footer> */}
        </>
    )
}

export default BlogsPage;
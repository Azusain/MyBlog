import React, {useEffect} from 'react'


import Footer from "./components/Footer";
import Header from "./components/Header";
import MainCon from "./components/MainCon";

import SearchBar from "./components/SearchBar";
import { BlogItem, BlogItemBeta} from "./components/ImageWithDetails";
import Collapse from "./components/Collapse";

import './output.css'

const BlogsPage: React.FC = () => {
    useEffect(() => {
        alert('Hello')
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
                        <Collapse topic="Computer Science" isCollapsed={true}></Collapse>
                        <Collapse topic="C++ Tricks" isCollapsed={true}></Collapse>
                    </div>
                    
                </div>
 
            </MainCon>
            
            <Footer></Footer>
        </>
    )
}

export default BlogsPage;
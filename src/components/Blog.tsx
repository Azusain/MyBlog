import ImageWithDetails from "./ImageWithDetails";
import MainCon from "./MainCon";

// Huge bug here!
const Blog: React.FC = () => {
    const blog_index = [1, 2, 3, 4];

    return (
        <div className="my-8 w-full">
            <div className="mt-20 mb-8">
                <MainCon width='46%' height='38rem' inner_layout='flex flex-col'>
                    <h2>From Blogs</h2>
                </MainCon>
            </div>
            <MainCon width="46%" height="15rem" inner_layout="flex flex-row gap-4 place-content-center">
                {blog_index.map((val, idx) => {
                    return (
                        <ImageWithDetails key={idx}></ImageWithDetails>
                    )
                })}
            </MainCon>
        </div>
    )
}

export default Blog;
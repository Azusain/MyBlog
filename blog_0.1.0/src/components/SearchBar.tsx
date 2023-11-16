import GuraButton from "./GuraButton";
import '../output.css'

const SearchBar: React.FC = () => {
    return (
        <div className="flex flex-row px-2">
            <input type="text" className="basis-3/4 my-2 p-2 border-2" ></input>
            <div className="basis-1/4 px-2"><GuraButton text="Search" onClick={() => {alert('啊sir才几篇文章啊就要搜索')}}></GuraButton ></div>
        </div>
    )
}

export default SearchBar;
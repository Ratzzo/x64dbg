#include "_scriptapi_bookmark.h"
#include "bookmark.h"

SCRIPT_EXPORT bool Script::Bookmark::Set(duint addr, bool manual)
{
    return BookmarkSet(addr, manual);
}

SCRIPT_EXPORT bool Script::Bookmark::Get(duint addr)
{
    return BookmarkGet(addr);
}

SCRIPT_EXPORT bool Script::Bookmark::GetInfo(duint addr, BookmarkInfo* info)
{
    BOOKMARKSINFO comment;
    if(!BookmarkGetInfo(addr, &comment))
        return false;
    if(info)
    {
        strcpy_s(info->mod, comment.mod);
        info->addr = comment.addr;
        info->manual = comment.manual;
    }
    return true;
}

SCRIPT_EXPORT bool Script::Bookmark::Delete(duint addr)
{
    return BookmarkDelete(addr);
}

SCRIPT_EXPORT void Script::Bookmark::DeleteRange(duint start, duint end)
{
    BookmarkDelRange(start, end);
}

SCRIPT_EXPORT void Script::Bookmark::Clear()
{
    BookmarkClear();
}

SCRIPT_EXPORT bool Script::Bookmark::GetList(ListOf(CommentInfo) listInfo)
{
    std::vector<BOOKMARKSINFO> bookmarkList;
    BookmarkGetList(bookmarkList);
    std::vector<BookmarkInfo> bookmarkScriptList;
    bookmarkScriptList.reserve(bookmarkList.size());
    for(const auto & bookmark : bookmarkList)
    {
        BookmarkInfo scriptComment;
        strcpy_s(scriptComment.mod, bookmark.mod);
        scriptComment.addr = bookmark.addr;
        scriptComment.manual = bookmark.manual;
        bookmarkScriptList.push_back(scriptComment);
    }
    return List<BookmarkInfo>::CopyData(listInfo, bookmarkScriptList);
}
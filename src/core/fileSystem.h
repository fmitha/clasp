#ifndef FileSystem_H //[
#define FileSystem_H
//stuff

#include "boost/filesystem.hpp"
#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include "core/object.h"
#include "iterator.h"
#include "pathname.fwd.h"

namespace core {


    SMART(Path);
    class Path_O : public T_O
    {
	friend class XmlSaveArchive_O;
	LISP_BASE1(T_O);
	LISP_CLASS(core,CorePkg,Path_O,"path");
	DECLARE_MAKE_INIT();
public:
#if defined(XML_ARCHIVE)
	void	archiveBase(ArchiveP node);
#endif // defined(XML_ARCHIVE)
	void	initialize();
private:
	boost_filesystem::path	_Path;
public:
	static Path_sp create(const string& path);
	static Path_sp create(boost_filesystem::path p);
	static Path_sp pathnameDesignator(T_sp obj);

public:
	boost_filesystem::path& getPath() { return this->_Path; };
public:

	/*! Comparison of paths */
	virtual bool lt(T_sp obj) const;

	bool isAbsolute() const { return this->_Path.is_absolute();};

	Path_sp copyPath() const;

	/*! Generate the boost_filesystem complete path */
	Path_sp absolute() const;

	/*! Return the POSIX time_t value for the last_write_time */
	Integer_sp last_write_time() const;

    void setPath(const boost_filesystem::path& p);
	void setPathFromString(const string& path);

	void sxhash(HashGenerator& hg) const;
	Path_sp parent_path();

	/*! Return just the fileName (*--end) as a string*/
	string fileName() const;

	/*! Return the path as a string */
	string asString() const;


	string __repr__() const;


		/*! If the fileName has aaa/bbbb/xxxx.yyy
		 * then the fileName is xxxx.yyy
		 * and this function only returns the xxxx part
		 * the prefix of the fileName
		 */
	string stem();

	/*! Return the extension */
	string extension();

	/*! Append to the extension with this new extension */
	void appendToExtension(string const& newExtension);

	/*! Replace the extension with this new extension */
	Path_sp replaceExtension(string const& newExtension);

	/*! Append a path component */
	Path_O& operator/=( string const& pp);

	/*! Append to the path - returns itself */
	Path_sp path_append(string const& pp);

	/*! Break the path up into parts. */
	Cons_sp parts() const;

	Cons_sp	glob(const string& globTemplate);

		/*! Return true if the file pointed to by this path exists */
	bool	exists();
	Path_O( const Path_O& ss ); //!< Copy constructor

	DEFAULT_CTOR_DTOR(Path_O);
    };

    


    SMART(DirectoryIterator );
    class DirectoryIterator_O : public Iterator_O
    {
	LISP_BASE1(Iterator_O);
	LISP_CLASS(core,CorePkg,DirectoryIterator_O,"DirectoryIterator");
	DECLARE_MAKE_INIT();
    public:
	void initialize();
    private:
	Path_sp _Path;
	/* A new CurrentIterator is created (new) whenever first() is called
	   So we have to manage the memory for _CurrentIterator
	 */
    boost_filesystem::directory_iterator* _CurrentIterator;
    boost_filesystem::directory_iterator  _EndIterator;
public:
    DirectoryIterator_sp create(Path_sp path, Lisp_sp lisp);
private:
	void setupCurrentIterator();
	void setPath(Path_sp  p);
    public:
	virtual void first();
	virtual void next();
	virtual bool isDone();
	virtual T_sp currentObject();
	explicit DirectoryIterator_O() : Base(), _CurrentIterator(NULL) {};
	virtual ~DirectoryIterator_O();
    };








    SMART(RecursiveDirectoryIterator );
    class RecursiveDirectoryIterator_O : public Iterator_O
    {
	LISP_BASE1(Iterator_O);
	LISP_CLASS(core,CorePkg,RecursiveDirectoryIterator_O,"RecursiveDirectoryIterator");
	DECLARE_MAKE_INIT();
    public:
	void initialize();
    private:
	Path_sp _Path;
	bool	_EnterHidden;
	/* A new CurrentIterator is created (new) whenever first() is called
	   So we have to manage the memory for _CurrentIterator
	 */
    boost_filesystem::recursive_directory_iterator* _CurrentIterator;
    boost_filesystem::recursive_directory_iterator  _EndIterator;
public:
    RecursiveDirectoryIterator_sp create(Path_sp path, Lisp_sp lisp);
private:
	void setupCurrentIterator();
	void setPath(Path_sp  p);
	void setHidden(bool b) { this->_EnterHidden = b;};
    public:
	virtual void first();
	virtual void next();
	virtual bool isDone();
	virtual T_sp currentObject();
	explicit RecursiveDirectoryIterator_O() : Base(), _CurrentIterator(NULL) {};
	virtual ~RecursiveDirectoryIterator_O();
    };




    SMART(FileStatus);

    SMART(DirectoryEntry );
    class DirectoryEntry_O : public T_O
    {
	LISP_BASE1(T_O);
	LISP_CLASS(core,CorePkg,DirectoryEntry_O,"DirectoryEntry");
    public:
	void initialize();
    private:
	boost_filesystem::directory_entry* _Entry;
public:
    void setEntry(const boost_filesystem::directory_entry& entry);
public:
    FileStatus_sp fileStatus();
    FileStatus_sp symlinkStatus();
    Path_sp path();
    explicit DirectoryEntry_O() : DirectoryEntry_O::Base(), _Entry(NULL) {};
    virtual ~DirectoryEntry_O();
    };





    SMART(FileStatus );
    class FileStatus_O : public T_O
    {
	LISP_BASE1(T_O);
	LISP_CLASS(core,CorePkg,FileStatus_O,"FileStatus");
public:
	void initialize();
private:
    boost_filesystem::file_status _FileStatus;
public:
    void setFileStatus(const boost_filesystem::file_status& fs);
public:
    bool exists();
    bool isRegularFile();
    bool isDirectory();
    bool isSymlink();
    bool isOther();
    DEFAULT_CTOR_DTOR(FileStatus_O);
    };




//    extern void rename_file(Path_sp src, Path_sp dest);
//    extern bool delete_file(Path_sp dest);





};




TRANSLATE(core::Path_O);
TRANSLATE(core::DirectoryIterator_O);
TRANSLATE(core::RecursiveDirectoryIterator_O);
TRANSLATE(core::DirectoryEntry_O);
TRANSLATE(core::FileStatus_O);



namespace core {
    Pathname_sp homedirPathname(Str_sp head); // See ecl_homedir_pathname

    /*! Return the current working directory as a string, if bool change_d_p_d then
     Change *default-pathname-defaults* to cwd */
    Pathname_sp getcwd(bool change_d_p_d=false);

};
#endif //]

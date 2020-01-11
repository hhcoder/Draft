#include <sys/time.h>
#include <iostream>
#include <map>
#include <vector>
#include <cstring>

class ConfigReader
{
public:
    ConfigReader(std::string& in_file_path)
        : src_path(in_file_path)
    {
        const char* ifname = in_file_path.c_str();
        FILE* fp = fopen(ifname, "r");
        if (NULL == fp)
        {
            throw std::string("Error opening config file: " + in_file_path); 
        }

        char key[512];
        char value[512];

        while (EOF != fscanf(fp, "%s", key) &&
            EOF != fscanf(fp, "%s", value) )
        {
            Add(std::string(key), std::string(value));
        }

        fclose(fp);
    }

    std::string Get(std::string& in_key)
    {
		std::map<std::string, std::string>::iterator iter = m_map.find(in_key);
		if (iter != m_map.end())
		{
			return iter->second;
		}
		else
		{
			throw std::string("cannot find requested key: "+in_key);
		}
    }

    std::string Get(const char* in_key)
    {
        std::string k(in_key);
        return Get(k);
    }

    int32_t GetInt(const char* in_key)
    {
        std::string s = Get(in_key);
        return atoi(s.c_str());
        // const char* t = s.c_str()
        // return atoi(t);
    }

    void Print()
    {
        std::cerr << "========================" << std::endl;
        std::cerr << "Config file " << src_path << "content: " << std::endl;

		for (std::map<std::string, std::string>::iterator iter = m_map.begin(); iter!=m_map.end(); iter++)
        {
            std::cerr << iter->first << " | " << iter->second << std::endl;
        }
        std::cerr << std::endl << "========================" << std::endl;
    }

private:
    void Add(const std::string& key, const std::string& value)
    {
        m_map.insert(std::pair<std::string, std::string>(key, value));
        std::cout << key << "," << value << std::endl;
    }

private:
    std::map<std::string, std::string> m_map;
    std::string src_path;
};

template <typename T>
class FileReader : public std::vector<vector<T>>
{
public:
    FileReader(
            std::string dir, 
            std::vector<std::string> &img_names,
            const size_t count 
            )
        : std::vector<vector<T>>(num_raws, vector<T>(count))
    {
        for (auto i : img_names)
        {
            try
            {
                std::shared_ptr<vector<T>> bin_src = new std::vector<T>(bin_size);

                std::string img_path(dir + "/" + i);
                ReadFromFile(img_path, bin_src, bin_size);

                this->push_back(bin_src);
            }

            catch (bad_alloc& ba) 
            {
                std::cerr << "ERROR: ";
                std::cerr << ba.what() << endl;
                throw ba;
            }
            catch(std::string& err)
            {
                std::cerr << err << std::endl;
                throw err;
            }
        }
    }

    ~FileReader()
    {
        for (auto i : buffers)
            delete(i);
    }

private:
    void ReadFromFile(std::string& in_fname, T* buf, const size_t len)
    {
        FILE* fp = fopen(in_fname.c_str(), "rb");
        if(NULL==fp)
        {
            std::string err("Error opening data file: " + in_fname);
            std::cout << err << std::endl;
            throw err;
        }
        if( len != fread(buf, 1, len, fp) )
        {
            std::string err("Error reading data file: " + in_fname);
            std::cout << err << std::endl;
            fclose(fp);
            throw err;
        }
        else
        {
            fclose(fp);
            std::cout << "Load " << in_fname << "..." << std::endl;
        }
    }
};


int main(int argc, char* argv[])
{
    if (argc < 2) 
    {
        std::cerr << "Usage: " << argv[0] << " config file path" << std::endl;
        return -1;
    }

    try
    {
        std::string in_file_path(argv[1]); 
        ConfigReader cfg(in_file_path);

        cfg.Print();

        std::string src_dir_path = cfg.Get("InputDirectoryPath");

        int raw_width = cfg.GetInt("InputRawWidth"); 

        int raw_height = cfg.GetInt("InputRawHeight");

        std::string raw_format = cfg.Get("InputRawFormat");

        std::string raw_color_seq = cfg.Get("InputRawColorSeq");

        std::string out_dir = cfg.Get("OutputDirectoryPath");

        std::string out_processed_name = cfg.Get("OutputStatsName");

        std::string out_processed_ext(".sts"); 

        std::cout << "raw data width: " << raw_width << std::endl;
        std::cout << "raw data height: " << raw_height << std::endl;
        std::cout << "raw color seq: " << raw_color_seq << std::endl;

        // Init function

        // Generate stats from raw data

        // Process function
        
        // Output results

    }
    catch(std::string& err)
    {
        std::cerr << err << std::endl;
        return -1;
    }
    return 0;
}

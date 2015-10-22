#!/usr/bin/ruby

require 'csv'

require 'nokogiri'
require 'open-uri'

base_sleep = 0
sleep_increment = 3
retries = 4

#http://www.nfl.com/liveupdate/game-center/2013090500/2013090500_gtd.json
#http://www.nfl.com/scores/2013/REG1

base_url = "http://www.nfl.com"

pro_picks = CSV.open("csv/pro_picks.csv","w",{:col_sep => "\t"})

# Header for team standings file

nfl_team_schedules << ["rank","player","best","worst","avg","sdev","pos"]

#Wk	Date	Game	Time (ET)	Attendance	Top Passer	Top Rusher	Top Receiver

team_schedules_url = "http://www.fantasypros.com/nfl/rankings/qb.php"

pro_picks_xpath = '//*[@id="data"]/tr[position()>2]'

doc = Nokogiri::HTML(open(team_schedules_url))
rescue
    sleep_time += sleep_increment
    print "sleep #{sleep_time} ... "
    sleep sleep_time
    tries += 1
    if (tries > retries)
      next
  else
      retry
  end
end

sleep_time = base_sleep

  #  print "#{year} #{team_name} ..."

doc.xpath(pro_picks_xpath).each do |player|

    row = [year,team_id]
    game.xpath("td").each_with_index do |field,j|
      # See String#encode
      text = field.text.strip rescue nil
      case j
      when 0
        values = field.xpath("a").flat_map do |node|
           [(node.text.strip rescue nil),
            (base_url+node.attributes["href"].text rescue nil),
            (node.next_sibling.text.gsub("@","").strip rescue nil)]
#          [(n.previous_sibling.text.strip rescue nil),
        end
        row += values
      when 1
        values = field.xpath("a").flat_map do |node|
           [(node.text.strip rescue nil),
            (base_url+node.attributes["href"].text rescue nil)]
#          [(n.previous_sibling.text.strip rescue nil),

        end
        row += values
      when 3..5
        values = field.xpath("a").flat_map do |node|
           [(node.text.strip rescue nil),
            (base_url+node.attributes["href"].text rescue nil),nil]
#            (node.next_sibling.next_sibling.text.strip rescue nil)]
#          [(n.previous_sibling.text.strip rescue nil),
        end
        row += values
      else
        row += [text]
      end

    end

    nfl_team_schedules << row


#      text = field.text.gsub("\t"," ").gsub("\r\n"," ").gsub("\r","").gsub("\n","").strip rescue nil
      
#      encoding_options = {
#        :invalid           => :replace,  # Replace invalid byte sequences
#        :undef             => :replace,  # Replace anything not defined in ASCII
#        :replace           => '',        # Use a blank for those replacements
#        :universal_newline => true       # Always break lines with \n
#      }
      #text = text.encode(Encoding.find('ASCII'), encoding_options)

#      case j
#      when 2
        #parts = text.split("\t")
=begin
        if (parts.size>1)
          status = parts[0].strip rescue nil
          game_name = parts[1].strip rescue nil
          link = field.xpath("a").first
          game_url = (base_url+link.attributes["href"].text) rescue nil
        else
          status = nil
          game_name = parts[0].strip rescue nil
          link = field.xpath("a").first
          game_url = (base_url+link.attributes["href"].text) rescue nil
        end
=end
#        row += [text]
#      else
        #parts = text.split("\t")
#        row += [text]
#      end
#    end
#    if (row.size>4) and not(row[4]=="W")

#    end

  end

end

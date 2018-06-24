# coding: utf-8

require 'stringio'

def negate_expr(s)
  s.gsub(/(^|\+|-)(\d+)/){
    if $1 == '-'
      '+' + $2
    else
      '-' + $2
    end
  }
end

def trans_expr(s)
  s = s.dup
  s.gsub!(/\+|\-/){|m| ' ' + m }
  s.gsub!(/\*/, ' ')
  s.gsub!(/=L=/, '<=')
  s.gsub!(/=E=/, '=')
  s.gsub!(/=G=/, '>=')
  s.strip!

  if /^(.*)<=(.*)$/ =~ s
    lhs = $1
    rhs = $2
    lhs = negate_expr(lhs)
    rhs = (- rhs.to_i).to_s
    s = lhs + ">=" + rhs
  end

  s.gsub!(/(=|>=|<=)/) { ' ' + $1 + ' ' }
  s
end

def add_coeffs(s)
  s = s.dup
  s.strip!
  s = "+" + s if /^\d+/ =~ s
  s.gsub!(/(\+|-|^)(x\d+|objvar)/) {
    if $1 == '-'
      '-1*' + $2
    else
      '+1*' + $2
    end
  }
  s
end

def trans(s, out)
  if /Solve m using %MINLP% minimizing objvar;/ =~ s
    min = true
  elsif /Solve m using %MINLP% maximizing objvar;/ =~ s
    min = false
  else
    raise RuntimeError.new("failed to detect optimization direction")
  end

  /^Variables (.*?);/mi =~ s
  vs = $1.split(/\s*,\s*/)

  vs.each{|v|
    if v == "objvar"
      next
    elsif /b\d+/ =~ v
      next
    else
      raise RuntimeError.new("unknown variable #{v.inspect}")
    end
  }
  
  cs = []
  s.scan(/^\w+\.\.\s+(.*?);/mi){|c,| cs.push c }

  cs.map!{|c|
    c.gsub!(/\s+/m, '')
    c.gsub!(/b(\d+)/){ 'x' + $1 }
    c.gsub!(/^\((.*?)\)-/){ $1 + '-' } # for hmittelman.gms
    /^(.*)(=.=)(.*)$/ =~ c
    lhs = $1
    op  = $2
    rhs = $3
    add_coeffs(lhs) + op + rhs
  }
  
  cs1 = []
  cs2 = []
  
  cs.each{|c|
    if /objvar/ =~ c
      cs2.push c
    else
      cs1.push c
    end
  }
  
  if cs2.size == 1
    obj_offset = nil
    obj_scaled = 1
    
    if min
      case cs2[0]
      when /^(.*)-1\*objvar=E=0$/i
        # translate "min objvar s.t. A-objvar=0" into "min A"
        obj = add_coeffs($1)
      when /^-\((.*)\)\+1\*objvar=E=0$/i
        # translate "min objvar s.t. -A+objvar=0" into "min A"
        obj = add_coeffs($1)
      when /^(.*)-1\*objvar=L=0$/i
        # translate "min objvar s.t. A-objvar<=0" into "min A"
        obj = add_coeffs($1)
      when /^(.*)\+1\*objvar=G=(\d+(\.\d+)?)$/i
        # translate "min objvar s.t. A+objvar>=B" into "min -A+B"
        # edgecross, faclay
        obj = $1
        obj_offset = $2
        obj = negate_expr(add_coeffs(obj))
      else
        raise RuntimeError.new("objvar occurs in unknown shape: #{cs2[0].inspect}")
      end
    else
      case cs2[0]
      when /^(.*)\+1\*objvar=L=0$/i
        # translate "max objvar s.t. A+objvar<=0" into "min A"
        # sporttournament
        obj = $1
        obj_scaled *= -1
      else
        raise RuntimeError.new("objvar occurs in unknown shape: #{cs2[0].inspect}")
      end
    end
  
    nvar = 0
    obj.scan(/x(\d+)/){ nvar = [nvar, $1.to_i].max }
    cs1.each{|c| c.scan(/x(\d+)/){ nvar = [nvar, $1.to_i].max } }

    unless obj_offset.nil?
      nvar += 1
      obj += "+#{obj_offset}*x#{nvar}"
      cs1 << "+1*x#{nvar}=1"
    end

    # cardqp_inlp.gms, cardqp_iqp.gms and faclay80.gms contain floating point
    # coefficients in objective function
    if /\./ =~ obj
      coeffs = []
      obj.scan(/(\+|-)(\d+(\.\d+)?)/){ coeffs.push(Rational($2)) }

      lcm = 1
      gcd = nil
      coeffs.each{|r|
        lcm = lcm.lcm(r.denominator)
        gcd = gcd.nil? ? r.numerator : gcd.gcd(r.numerator)
      }

      obj_scaled = obj_scaled * Rational(lcm, gcd)

      obj_orig = obj.dup
      obj.gsub!(/(\+|-)(\d+(\.\d+)?)/){|coeff|
        coeff = Rational(coeff) * lcm / gcd
        if coeff.numerator >= 0
          "+" + coeff.numerator.to_s
        else
          coeff.numerator.to_s
        end
      }
      raise RuntimeError.new "#{obj_orig} -> #{obj}" if /--/ =~ obj
    end

    if obj_scaled != 1
      puts "objective function is scaled by #{obj_scaled}"
    end

    # the BNF of OPB file requires at least one constraint, so we add a dummy one.
    if cs1.empty?
      cs1 << "+1*x1=G=0"
      nvar = [nvar, 1].max
    end

    products = []
    obj.gsub!(/x\d+(\*x\d+)*/){|s|
      xs = []
      s.scan(/x(\d+)/){ xs.push($1.to_i) }
      xs.sort!
      products.push xs if xs.size > 1
      s2 = xs.map{|n| "x" + n.to_s }.join("*")
      #puts "#{s} -> #{s2}" if s != s2      
      raise RuntimeError.new("#{s.inspect}.size != #{s2.inspect}.size") if s.size != s2.size
      s2
    }

    products.uniq!
    sizeproduct = 0
    products.each{|xs| sizeproduct += xs.size }

    out.puts "* #variable= #{nvar} #constraint= #{cs1.size} #product= #{products.size} sizeproduct= #{sizeproduct}"
    out.puts "min: #{trans_expr(obj)} ;"
    cs1.each{|c|
      out.puts "#{trans_expr(c)} ;"
    }
  else
    raise RuntimeError.new("objvar occurs multiple times")
  end
end

def process(fname)
  fname2 = File.join("..", "opb", File.basename(fname, ".gms") + ".opb")
  puts "#{fname} -> #{fname2}"

  s = File.read(fname)
  File.open(fname2, "wb"){|f|
    trans(s, f)
  }
end

Dir["../gms/*.gms"].each{|fname|
  process(fname)
}
